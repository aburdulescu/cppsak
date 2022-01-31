#!/bin/bash

set -x

version=$(cat version.txt)
releasedir=release-$version
tool_name=cppsak

rm -rf $releasedir
mkdir -p $releasedir

docker cp $tool_name"_builder":/$tool_name/b/$tool_name $releasedir/

cd $releasedir

strip $tool_name
gzip -k $tool_name
sha512sum $tool_name.gz > $tool_name.gz.sha512
