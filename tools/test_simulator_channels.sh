#!/bin/sh
# Exercise the actual Simulator.cpp path, not a second backend implementation.
set -eu
cd "$(dirname "$0")/.."
mkdir -p build/rx-channels
for variant in normal sanitize;do
 flags='-O2'
 if [ "$variant" = sanitize ];then flags='-O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer';fi
 c++ -std=c++17 $flags -Wall -Wextra -Werror -Wno-misleading-indentation -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-private-field -Wno-sign-compare -Wno-deprecated-declarations \
  -funsigned-char -DARDUINO=10800 -DMESHIS_V2=1 -DMESHIS_LIVE_RADIO=1 -DBRAND_CLASSIC_UI=1 -DLU_ALERT_BRANDING=1 \
  -I simulator/src -I simulator/shims -I simulator/vendor/adafruit-gfx -I vendor/meshcore/src -I vendor/meshcore -I firmware/core -I firmware/ui -I firmware/display \
  tests/simulator_channels_test.cpp simulator/src/Simulator.cpp simulator/vendor/adafruit-gfx/Adafruit_GFX.cpp -o build/rx-channels/simulator-$variant
 ./build/rx-channels/simulator-$variant
done
