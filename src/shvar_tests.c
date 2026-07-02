#include "../headers/minishell.h"

int	main(void)
{
	t_var_arr *varr = var_arr_create();
	char str1[] = "var1=testtesttest";
	char str2[] = "var2=";
	char str3[] = "var3=dupa";
	char str4[] = "var4=sraka";
	char *p1;
	char *p2;

	ft_printf("%s\n%s\n%s\n%s\n\n%d\n\n\n\n", p1 = get_name_from_full_var(str1),
		get_value_from_full_var(str1), p2 = get_name_from_full_var(str2),
		get_value_from_full_var(str2), get_value_from_full_var(str2)[0] == 0);

	free(p1);
	free(p2);
	set_shell_var_value(varr, "var1", get_value_from_full_var(str1));
	set_shell_var_value(varr, "var2", get_value_from_full_var(str2));
	set_shell_var_value(varr, "var3", get_value_from_full_var(str3));

	ft_printf("%s\n%s\n\n", get_shell_var_value(varr, "var1"),
		get_shell_var_value(varr, "var3"));

	set_shell_var_value(varr, "var3", "sraka_wilkolaka");
	ft_printf("%s\n%s\n\n", get_shell_var_value(varr, "var1"),
		get_shell_var_value(varr, "var3"));

	ft_printf("\n\nVALUE AT INDEX 0: %s\n\n", varr->var_arr[0]);

	remove_shell_var(varr, "var1");
	ft_printf("%s\n%s\n\n", get_shell_var_value(varr, "var1"),
		get_shell_var_value(varr, "var3"));

	set_shell_var_value(varr, "var4",
		get_value_from_full_var(str4));
	ft_printf("\n\nVALUE AT INDEX 0: %s\n\n", varr->var_arr[0]);

	set_shell_var_value(varr, "x1", "asdasd");
	set_shell_var_value(varr, "x2", "wartosc");
	set_shell_var_value(varr, "x3", "tooo kure jest");
	set_shell_var_value(varr, "x4", "wartosc");
	set_shell_var_value(varr, "x5", "taktka");
	set_shell_var_value(varr, "x6", "tojesto");

	ft_printf("\n\n%s\n%s\n%s\n\n", get_shell_var_value(varr, "x1"),
		get_shell_var_value(varr, "x3"), get_shell_var_value(varr, "x5"));

	set_shell_var_value(varr, "x1", "INNA WARTOSC");
	remove_shell_var(varr, "x2");
	ft_printf("%s\n%s\n\n", get_shell_var_value(varr, "x1"),
		get_shell_var_value(varr, "x2"));

	set_shell_var_from_full_var(varr, "varka1=adsasdasd");
	set_shell_var_from_full_var(varr, "varka2=testuje");
	set_shell_var_from_full_var(varr, "varka3=dupeee");
	ft_printf("\n%s\n%s\n%s\n\n", get_shell_var_value(varr, "varka1"), get_shell_var_value(varr, "varka2"), get_shell_var_value(varr, "varka3"));
	
	ft_printf("\n\n\nsize: %d\nallocated_size: %d", varr->size, varr->allocated_size);
	var_arr_free(varr);

	return (0);
}