ARGS=$@

git add .
git status
git commit -m "$ARGS"
git push -u origin main