#!/usr/bin/env bash

# sync the branch tsc_adept to the last change in upstream/master qmk

git switch master
git fetch upstream
git merge --ff-only upstream/master
git push origin master

git switch tsc_adept
git merge master
git push
