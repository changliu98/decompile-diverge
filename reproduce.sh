#!/bin/bash
# Re-score every shipped candidate on the frozen corpora, run every candidate through its corpus's
# own shipped tests, re-measure corpus coverage, and check all of it against the paper.
#
#   ./reproduce.sh                    # everything, 8 parallel containers
#   JOBS=32 ./reproduce.sh            # more parallel containers (each capped at 16 GB)
#   SAMPLE=0.2 ./reproduce.sh         # a stratified 20% of the functions, every system on each
#   SAMPLE=0.2 SEED=7 ./reproduce.sh  # a different 20%
#   LIMIT=5 ./reproduce.sh            # trial run: the first 5 functions of each group
#   GROUPS_TO_RUN="cve_barebone" ./reproduce.sh
#
# Resumable: a pair that already has a result under results/ is skipped.
set -u
cd "$(dirname "$0")"

JOBS="${JOBS:-8}"
LIMIT="${LIMIT:-0}"
SAMPLE="${SAMPLE:-}"
SEED="${SEED:-2027}"
GROUPS_TO_RUN="${GROUPS_TO_RUN:-humaneval anghabench mbpp exebench github_barebone cve_barebone}"

if ! docker image inspect ddiv-oracle:22.04 >/dev/null 2>&1; then
  echo "image ddiv-oracle:22.04 not found -- run ./build_image.sh first" >&2
  exit 1
fi

SEL=()
if [ -n "$SAMPLE" ]; then
  python3 oracle/sample.py --fraction "$SAMPLE" --seed "$SEED" --out results/sample.txt || exit 1
  SEL=(--bundles-file results/sample.txt)
fi

# 1) the differential-fuzzing oracle on the frozen corpora
for g in $GROUPS_TO_RUN; do
  echo "== $(date -u +%FT%TZ) group=$g jobs=$JOBS limit=$LIMIT ${SAMPLE:+sample=$SAMPLE}"
  python3 oracle/difffuzz_group.py --group "$g" --jobs "$JOBS" --limit "$LIMIT" "${SEL[@]}" || exit 1
done

# 2) the corpora's own shipped tests (Pass, Div|P): HumanEval, MBPP, ExeBench
TEST_GROUPS=""
for g in $GROUPS_TO_RUN; do
  case "$g" in humaneval|mbpp|exebench) TEST_GROUPS="${TEST_GROUPS:+$TEST_GROUPS,}$g" ;; esac
done
if [ -n "$TEST_GROUPS" ]; then
  echo "== $(date -u +%FT%TZ) shipped tests: $TEST_GROUPS"
  python3 oracle/shipped_tests.py --groups "$TEST_GROUPS" --jobs "$JOBS" --limit "$LIMIT" \
      "${SEL[@]}" || exit 1
fi

# 3) line/branch coverage of the frozen corpora
echo "== $(date -u +%FT%TZ) coverage"
python3 oracle/coverage.py --groups "$(echo $GROUPS_TO_RUN | tr ' ' ',')" --jobs "$JOBS" \
    --limit "$LIMIT" "${SEL[@]}" || exit 1

python3 oracle/tables.py --results
echo
python3 oracle/tables.py --compare
