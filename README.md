# Intérprete de lenguaje de caras

# Proyecto final de la materia de compiladores FCC BUAP

# Componentes
- Analizador léxico manual, hecho con tabla de transiciones y autómata
- Analizador sintáctico descendente predictivo
- Analizador semántico (solo comprobación de tipos y generación de instrucciones)
- Intérprete

# Ejemplo del lenguaje de caras:

```
creaCara(Ricardo, 20, 2)
cambiaEstadoOjo(Ricardo, izquierdo, cerrado)
si cerrado = estadoOjoIzq entonces
    cambiaEstadoOjo(Ricardo, derecho, cerrado)
finSi

ciclo 3
    si abierto = estadoOjoIzq entonces        
        cambiaEstadoOjos(Ricardo, abierto)
        cambiaEstadoBoca(Ricardo, sonriente)
    sino
        cambiaEstadoOjos(Ricardo, cerrado)
        cambiaEstadoBoca(Ricardo, triste)
    finSi
finCiclo

creaCara(Atenea, 15, 2)
cambiaEstadoOjos(Atenea, cerrado)
```