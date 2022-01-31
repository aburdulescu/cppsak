#!/bin/bash

docker build -t cppsak_builder .

mkdir -p ~/tmp/cppsak_ccache/

docker run \
       -it \
       --rm \
       --name cppsak_builder \
       -v $HOME/tmp/cppsak_ccache/:/ccache \
       -v $(pwd):/cppsak \
       cppsak_builder
