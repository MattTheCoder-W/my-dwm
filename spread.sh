#!/bin/bash

scripts="sbar volume.sh"
if [[ ! -d "scripts" ]]; then
	echo ">> scripts directory not found! pull repo again!"
	exit 1
fi
missing=0
for script in $scripts; do
	if [[ ! $(echo $(ls scripts/) | grep -w $script) ]]; then
		echo ">> script $script not found! pull repo again!"
		missing=1
	fi
done
if [[ $missing -eq 1 ]]; then
	echo ">> There are missing scripts"
	exit 1
else
	echo ">> No missing scripts"
fi

if [[ ! -d "/usr/local/share/dwm" ]]; then
	echo ">> Creating /usr/local/share/dwm"
	sudo mkdir /usr/local/share/dwm
fi

echo ">> Copying files"
for script in $scripts; do
	echo -e "\t>> Copying $script"
	sudo cp scripts/$script /usr/local/share/dwm/$script
done

echo ">> DONE!"
