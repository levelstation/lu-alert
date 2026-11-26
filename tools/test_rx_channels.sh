#!/bin/sh
# Native Wio-LU display/filter and actual prepared RX-hook tests. No device access.
set -eu
cd "$(dirname "$0")/.."
mkdir -p build/rx-channels
python3 tools/setup_firmware.py
python3 - <<'PY'
from pathlib import Path
import hashlib,subprocess
path=Path('upstream/examples/companion_radio/ui-new/UITask.cpp')
initial=path.read_bytes()
subprocess.run(['python3','tools/setup_rx_channels_ui.py','apply'],check=True)
assert path.read_bytes()==initial,'Applying channel hook twice changed source'
subprocess.run(['python3','tools/setup_rx_channels_ui.py','strip'],check=True)
assert path.read_bytes()!=initial,'Channel hook strip did not remove known addition'
subprocess.run(['python3','tools/setup_rx_channels_ui.py','apply'],check=True)
assert path.read_bytes()==initial,'Channel hook round trip changed prepared source'
source=path.read_text();start=source.index('void UITask::onChannelMessageRecv(')
start=source.index('#if defined(LU_ALERT_RX_CHANNELS)',start)
end=source.index('#endif',start)+len('#endif')
Path('build/rx-channels/rx-channel-callback.inc').write_text(source[start:end]+'\n')
print('PASS: actual prepared RX callback and reversible/idempotent channel hook')
PY
for variant in normal sanitize; do
 flags='-O2'
 if [ "$variant" = sanitize ];then flags='-O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer';fi
 c++ -std=c++17 $flags -Wall -Wextra -Werror -Wno-misleading-indentation -Wno-unused-parameter -Wno-deprecated-declarations \
  -funsigned-char -DARDUINO=10800 -DMESHIS_V2=1 -DLU_ALERT_BRANDING=1 \
  -I firmware/core -I firmware/ui -I firmware/display -I simulator/shims -I simulator/vendor/adafruit-gfx -I vendor/meshcore/src -I build/rx-channels \
  tests/rx_channels_test.cpp simulator/vendor/adafruit-gfx/Adafruit_GFX.cpp -o build/rx-channels/test-$variant
 ./build/rx-channels/test-$variant
done
