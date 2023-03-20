#!/bin/bash

# Setup xrandr monitor
# xrandr --output OUTPUT --mode 1920x1080 -r 60

# Set wallpaper
WP_DIR="/home/${USER}/.config/dwm/wallpapers"
LEFT="arc.jpg"
RIGHT="arc.jpg"
feh --bg-tile $WP_DIR/$LEFT --bg-fill $WP_DIR/$RIGHT

# Startup volume
pactl set-sink-volume 0 20%

# Startup bar
/usr/local/share/dwm/sbar &

