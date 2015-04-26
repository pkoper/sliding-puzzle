#!/bin/sh

/bin/find . -iregex '.*\.\(h\|cc\)' -print0 | xargs -0 ./cpplint.py -- 2>&1
