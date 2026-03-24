Proyecto realizado por alumnos de la facultad de ingenieria de la UAEMex,
para la materia de sistemas embebidos.

-Luis Ricardo Serrano Dzib
-Aram Gonzales Ronquillo

Este proyecto tiene el fin de poder cultivar algas y mantenerlas en buen estado para podsteriormente usarlas como combustible o darle distintas utilidades, por lo que este
bioreactor tiene el objetivo de dar condiciones aptas a las algas para que su crecimiento 
sea el adecuado, esto, por medio del monitoreo de variables criticas para su crecimiento.

Las librerias que necesitamos importar son:

#libreria para graficos
idf.py add-dependency "nixy4/u8g2^0.1.0"

#sensor de temperatura
idf.py add-dependency "espressif/onewire_bus"
idf.py add-dependency "espressif/ds18b20"