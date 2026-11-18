# The one image the oracle runs everything inside: Ubuntu 22.04, the clang/LLVM 14 toolchain,
# AFL++, and the -dev libraries the benchmark drivers were built against.
#
#   build:  ./build_image.sh        (or: docker build -t ddiv-oracle:22.04 .)
#
# The network is used ONLY here, at build time (apt). Every container the oracle starts from
# this image runs with `--network none` and a memory cap (see oracle/difffuzz.py).
FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

# clang/llvm on 22.04 are the 14.x series (clang, llvm-cov-14, llvm-profdata-14): the
# sanitizer-free builds and the coverage measurement use them. binutils provides nm/readelf
# (the by-symbol exit-state compare); setarch ships in the base image (util-linux).
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential clang llvm lld gcc g++ make \
        cmake meson ninja-build \
        autoconf automake autoconf-archive libtool pkg-config m4 gettext gperf \
        bear binutils file xxd patch \
        git ca-certificates \
        python3 python3-pip \
        zlib1g-dev libssl-dev libbz2-dev liblzma-dev libzstd-dev liblz4-dev \
        libpcre2-dev libpcre3-dev libexpat1-dev libxml2-dev libxslt1-dev \
        libcurl4-openssl-dev libjpeg-dev libpng-dev libffi-dev libgmp-dev \
        libncurses-dev libreadline-dev uuid-dev libsqlite3-dev libyaml-dev \
        libnghttp2-dev libidn2-dev libssh2-1-dev libkrb5-dev libpcap-dev \
        nasm yasm \
        libtiff-dev libwebp-dev libfreetype6-dev libfontconfig1-dev libgif-dev \
        libvorbis-dev libogg-dev libtheora-dev libopus-dev libvpx-dev libmp3lame-dev \
        libx11-dev libxext-dev libxfixes-dev libxrandr-dev libxcursor-dev libxi-dev libxkbcommon-dev \
        libasound2-dev libpulse-dev libsdl2-dev libass-dev \
    && rm -rf /var/lib/apt/lists/*

# AFL++ WITH its recommended packages: afl-clang-fast drives clang 13, and the clang 13 ASan
# runtime symbolizes crash stacks with /usr/lib/llvm-13/bin/llvm-symbolizer, which only the
# recommended llvm-13 package provides. Without it stacks stay unsymbolized and the oracle's
# crash identity (sanitizer check + faulting function) silently degrades.
RUN apt-get update && apt-get install -y afl++ bison flex && rm -rf /var/lib/apt/lists/*

# Every tool the oracle invokes must be on PATH, or the build fails here.
RUN command -v afl-fuzz && command -v afl-clang-fast \
    && command -v clang && command -v llvm-cov-14 && command -v llvm-profdata-14 \
    && command -v llvm-symbolizer && command -v llvm-symbolizer-13 \
    && command -v nm && command -v readelf && command -v setarch && echo "toolchain ready"

# Self-test: an ASan report from an afl-clang-fast build must name the faulting function.
RUN mkdir /tmp/selftest && cd /tmp/selftest \
    && printf '#include <stdlib.h>\nint victim(int *p, int n) { return p[n]; }\nint main(void) { int *a = malloc(16); return victim(a, 5); }\n' > t.c \
    && AFL_USE_ASAN=1 afl-clang-fast -fsanitize=address -fno-omit-frame-pointer -g -O1 -o t t.c >/dev/null 2>&1 \
    && (ASAN_OPTIONS=symbolize=1:detect_leaks=0 ./t 2>report.txt || true) \
    && grep -q "in victim" report.txt && echo "symbolization ready" \
    && cd / && rm -rf /tmp/selftest

WORKDIR /work
