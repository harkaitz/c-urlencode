#!/bin/sh -e
url="https://github.com/harkaitz/c-urlencode"
sed -i '/Share with examples/,$d' README.md
if true; then
    echo "## Share with examples."
    echo ""
    for a in facebook twitter whatsapp linkedin; do
        echo "[Share with ${a}](`./tools/urlencode -t "${a}" "${url}"`)"
    done
    echo ""
fi >> README.md

