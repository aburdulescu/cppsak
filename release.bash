#!/bin/bash

set -x

version=$(cat version.txt)
releasedir=release-$version

rm -rf $releasedir
mkdir -p $releasedir

cp b/enums $releasedir/

cd $releasedir

strip enums
gzip -k enums
sha512sum enums.gz > enums.gz.sha512
