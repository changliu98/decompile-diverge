#!/bin/bash
# Build the oracle image from the shipped Dockerfile (apt only; a few minutes).
set -e
cd "$(dirname "$0")"
docker build -t ddiv-oracle:22.04 -f Dockerfile .
echo "built ddiv-oracle:22.04"
