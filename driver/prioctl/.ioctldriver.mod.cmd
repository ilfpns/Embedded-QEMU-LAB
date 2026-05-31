savedcmd_ioctldriver.mod := printf '%s\n'   ioctldriver.o | awk '!x[$$0]++ { print("./"$$0) }' > ioctldriver.mod
