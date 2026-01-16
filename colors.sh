#!/bin/bash

echo "256-color palette (foreground):"
echo

for i in {0..255}; do
	printf "\033[38;5;%sm%3d\033[0m " "$i" "$i"
	if (((i + 1) % 16 == 0)); then
		echo
	fi
done

echo
