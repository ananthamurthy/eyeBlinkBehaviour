#!/usr/bin/env bash
# Check if all permissions are set up.
GROUPS=`id -nG $USER`
for grp in dialout pgrimaging; do
    if echo $GROUPS | grep -qw '$grp'; then
        echo "ERR: $USER is not part of group $grp."
    else
        echo "OK: $USER is part of $grp"
    fi
done
