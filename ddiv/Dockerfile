FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 clang llvm afl++ binutils libc6-dev ca-certificates \
    && rm -rf /var/lib/apt/lists/*
RUN command -v afl-clang-fast && command -v afl-fuzz \
    && command -v llvm-symbolizer && command -v nm && command -v readelf
WORKDIR /work
