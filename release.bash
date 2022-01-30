#!/bin/bash

set -x

version=$(cat version.txt)
releasedir=release-$version

rm -rf $releasedir
mkdir -p $releasedir

docker cp enums_builder:/enums/b/cppsak $releasedir/

cd $releasedir

strip cppsak
gzip -k cppsak
sha512sum cppsak.gz > cppsak.gz.sha512
