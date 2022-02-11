#!/bin/sh

prefix="/home/m4t1/.config/dwm/"
args=$(cat ${prefix}screen-state.txt)

if [[ "$args" == "OFF" ]]; then
	xrandr --output HDMI-A-0 --right-of DisplayPort-2 --auto
	echo ON > ${prefix}screen-state.txt
elif [[ "$args" == "ON" ]]; then
	xrandr --output HDMI-A-0 --off
	echo OFF > ${prefix}screen-state.txt
fi
