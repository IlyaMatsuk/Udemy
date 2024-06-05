from prettytable import PrettyTable

table = PrettyTable()
table.add_column("Pokemon Name", ["Pi", "Sq", "Ch"])
table.add_column("Type", ["El", "Wa", "Fi"])
table.align = "l"

print(table)
