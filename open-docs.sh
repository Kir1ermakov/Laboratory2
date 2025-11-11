#!/usr/bin/env bash
set -e

if [ ! -f "build/docs/html/index.html" ]; then
  ./docs.sh
fi

DOCS_PATH="build/docs/html/index.html"

if [ ! -f "$DOCS_PATH" ]; then
  echo "Не найден файл документации: $DOCS_PATH"
  exit 1
fi

if command -v xdg-open >/dev/null 2>&1; then
  xdg-open "$DOCS_PATH" >/dev/null 2>&1 &
elif command -v open >/dev/null 2>&1; then
  open "$DOCS_PATH" >/dev/null 2>&1 &
elif command -v start >/dev/null 2>&1; then
  start "" "$DOCS_PATH" >/dev/null 2>&1 &
else
  echo "Не удалось определить команду для открытия браузера. Откройте вручную: $DOCS_PATH"
fi

echo "Открываю документацию: $DOCS_PATH"


