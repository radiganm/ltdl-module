#!/bin/bash
### test-loader.sh
### Mac Radigan

  d=${0%/*}; f=${0##*/}; n=${f%.*}; e=${f##*.}
  r=`readlink -f $d`
  root=$r/..

  set -euo pipefail
  IFS=$'\n\t'

  echo env MODULE_PATH=$root/.libs/ $root/loader --name libhello --args 25
  env MODULE_PATH=$root/.libs/ $root/loader --name libhello --args 25

### *EOF*
