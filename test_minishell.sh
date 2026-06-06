MINISHELL=./minishell
BASH=bash
BASH_OUTPUT=bash_output.log

MSH_OUTPUT=msh_output.log

TEST_COUNT=0

run_test() {
	local cmd=$1

	echo $cmd | $MINISHELL >$MSH_OUTPUT.stdout 2>$MSH_OUTPUT.stderr
	local MSH_EXIT_CODE=$?

	echo $cmd | $BASH >$BASH_OUTPUT.stdout 2>$BASH_OUTPUT.stderr
	local BASH_EXIT_CODE=$?

	local failed=0

	#Compare stdout
	diff $BASH_OUTPUT.stdout $MSH_OUTPUT.stdout >/dev/null
	if [ $? -ne 0 ]; then
		failed=1
		echo "[FAIL] STDOUT mismatch"
		diff $BASH_OUTPUT.stdout $MSH_OUTPUT.stdout
	fi

	#Compare stderr
	diff $BASH_OUTPUT.stderr $MSH_OUTPUT.stderr >/dev/null
	if [ $? -ne 0 ]; then
		failed=1
		echo "[FAIL] STDERR mismatch"
		diff $BASH_OUTPUT.stderr $MSH_OUTPUT.stderr
	fi

	#Compare exit codes
	if [ $BASH_EXIT_CODE -ne $MSH_EXIT_CODE ]; then
		failed=1
		echo "[FAIL] Exit code mismatch: Bash=$BASH_EXIT_CODE, Minishell=$MSH_EXIT_CODE"
	fi

	if [ $failed -eq 0 ]; then
		echo "[OK]"
	fi
	echo "------------------------------------"
}

run_tests() {
	tests=(
		"ls"
		"echo Hello, World!"
		"cat nonexistent_file"
		"ls -l /"
		"ls|grep obj"
		"ls libft -l | grep .c"
		"false_command"
		"sleep 1"
		"ls | sort"
		"cat /etc/passwd | grep root"
		"cd /tmp && pwd"
	)
	local test_amount=${#tests[@]}
	local test_count=0
	echo "Running $test_amount tests for Minishell..."
	for test in "${tests[@]}"; do
		((test_count++))
		echo "Test $test_count/$test_amount: '$test'"
		run_test "$test"
	done
}

run_tests
