#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
# Wio only: the Heltec preview and its published assets are not rebuilt.
sh tools/test_text_scroll_web.sh
node tests/rx_channels_web_test.mjs
