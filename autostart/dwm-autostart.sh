#!/bin/bash

# Setup dual monitor
~/.screenlayout/rightvert.sh

# Set wallpaper
WP="/home/m4t1/.local/share/wallpapers/wall.png"
feh --bg-tile $WP --bg-fill $WP

# Startup volume
pactl set-sink-volume 0 50%

# Startup bar
/usr/local/share/dwm/sbar &

