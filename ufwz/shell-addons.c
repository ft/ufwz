#include <init.h>
#include <shell/shell.h>
#include <zephyr.h>

#include <stdarg.h>
#include <stdlib.h>

#include <c/register-table.h>
#include <c/register-utilities.h>

void
ufw_shell_fprintf(void *dst, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    shell_vfprintf(dst, SHELL_NORMAL, fmt, args);
    va_end(args);
}

int
ufw_shell_addons_init(const struct device *dev)
{
    (void)dev;
    register_set_printer(ufw_shell_fprintf);
    return 0;
}

SYS_INIT(ufw_shell_addons_init, PRE_KERNEL_1, 0);

static RegisterTable *table = NULL;

void
ufw_shell_reg_init(RegisterTable *t)
{
    table = t;
}

static void
outofrange(struct shell *shell, long int n)
{
    ufw_shell_fprintf(shell, "Argument out of range: %ld\n", n);
}

static int
print_by_handle(struct shell *shell, RegisterHandle h)
{
    RegisterEntry* e = register_get_entry(table, h);
    if (e == NULL) {
        outofrange(shell, h);
        return -1;
    }
    register_entry_print(shell, "", e);
    return 0;
}

static void
print_current(struct shell *shell, RegisterHandle h)
{
    RegisterValue value;
    RegisterAccess rv = register_get(table, h, &value);
    if (rv.code != REG_ACCESS_SUCCESS) {
        ufw_shell_fprintf(shell, "register_get(): %d, %s\n",
                          (int)rv.code,
                          register_accesscode_to_string(rv.code));
    } else {
        ufw_shell_fprintf(shell, "    Current Value   : ");
        register_value_print(shell, &value);
        ufw_shell_fprintf(shell, "\n");
    }
}

void
ufw_shell_regshow(const struct shell *s, size_t argc, char **argv)
{
    void *shell = (void*)s;
    if (table == NULL) {
        ufw_shell_fprintf(shell, "No register table found.\n");
        return;
    }
    if (argc == 1u) {
        register_table_print(shell, "", table);
    } else if (argc == 2u) {
        long int reg = strtol(argv[1], NULL, 10u);
        if (reg < 0) {
            outofrange(shell, reg);
            return;
        }
        if (print_by_handle(shell, reg) == 0) {
            print_current(shell, reg);
        }
    } else {
        ufw_shell_fprintf(shell, "usage: regshow [HANDLE : Integer]\n");
    }
}

SHELL_CMD_REGISTER(regshow, NULL,
                   "Show register table item",
                   ufw_shell_regshow);
