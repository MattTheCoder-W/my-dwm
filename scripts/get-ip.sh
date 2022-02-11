#!/bin/sh

ipv6=$(curl -s https://www.whatismyip.com/ | grep -oP '<a id="(ipv6|ipv4)".*</a>' | grep -oP '">.*</a>' | sed -e 's/>/\n/g' -e 's/</\n/g' | head -2 | tail -1)
ipv4=$(curl -s ifconfig.me)

echo 6=$ipv6
echo 4=$ipv4
