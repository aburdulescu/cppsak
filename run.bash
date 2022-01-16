#!/bin/bash

docker build -t enums_builder .

mkdir -p ~/tmp/enums_ccache/

docker run \
       -it \
       --rm \
       --name enums_builder \
       -v $HOME/tmp/enums_ccache/:/ccache \
       -v $(pwd):/enums \
       enums_builder
