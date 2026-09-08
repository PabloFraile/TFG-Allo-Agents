from allo.customize import Partition

print("=== Partition (importado directamente de allo.customize, el módulo) ===")
print(Partition)
print("Tipo:", type(Partition))
print()
print("=== Atributos públicos de Partition ===")
for nombre in dir(Partition):
    if not nombre.startswith("_"):
        valor = getattr(Partition, nombre)
        print(f"  Partition.{nombre} = {valor!r}")
