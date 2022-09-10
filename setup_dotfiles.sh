#! /bin/env sh

if [[ $LANG = "pt_BR.UTF-8" ]]; then
	echo "iniando script..."
else
	echo "starting script..."
fi

sudo xbps-install base-devel libX11-devel libXft-devel libXinerama-devel freetype-devel fontconfig-devel

echo "creating folders..."
mkdir -p Imagens/ && mkdir -p .conf/suckless

echo "copying dot files..."
cp -f -r {dwm,st,dmenu} /root/$HOME/.config/suckless





