#!/bin/bash
set -e

KEY_URL="https://repo.tohur.xyz/keys/rakuos.asc"
OUT_ASC="usr/share/keyrings/rakuos-archive-keyring.asc"
OUT_GPG="usr/share/keyrings/rakuos-archive-keyring.gpg"

mkdir -p usr/share/keyrings

echo "🔑 Downloading key from $KEY_URL..."
curl -fsSL "$KEY_URL" -o "$OUT_ASC"

echo "📦 Creating binary keyring..."
gpg --dearmor < "$OUT_ASC" > "$OUT_GPG"

wget -qO - https://dl.xanmod.org/archive.key | sudo gpg --dearmor -vo usr/share/keyrings/xanmod-archive-keyring.gpg
echo "✅ Keyring files ready:"
ls -l usr/share/keyrings/
