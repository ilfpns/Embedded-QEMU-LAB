savedcmd_logdriver.mod := printf '%s\n'   logdriver.o | awk '!x[$$0]++ { print("./"$$0) }' > logdriver.mod
