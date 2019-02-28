#!/bin/bash
test_free()
{
	local ok=0
	local ko=0
	for i in {1..20}
	do
		test0="$(./run.sh /usr/bin/time -l ./test0 2>&1 | grep reclaims | column -t)"
		test2="$(./run.sh /usr/bin/time -l ./test2 2>&1 | grep reclaims | column -t)"
		echo -e "test0: $test0\ntest2: $test2"
		test0="$(echo "$test0" | cut -d ' ' -f1)"
		test2="$(echo "$test2" | cut -d ' ' -f1)"
		diff=$((test2 - test0))
		echo -e "diff: $diff\n"
		if ((diff > 3)); then
			((ko++))
		else
			((ok++))
		fi
	done
	printf "Total OK: $ok\nTotal KO: $ko\n"
}

test_free
