The Contiki Operating System
============================

Carpeta que contiene el sistema operativo contiki personalizado para este TFM

Se recomienda su uso con Instan Contiki 2.7, maquina virtual preparada para ejecutar ContikiOS, se puede descargar del siguiente link: https://sourceforge.net/projects/contiki/files/Instant%20Contiki/Instant%20Contiki%202.7/

El usuario debe de remplazar el contenido de la carptea contiki ubicada en /home/

![carpeta](https://drive.google.com/uc?export=view&id=15d6hNfyCEmNimF066bhgSedj2lgiJ8mX)

Estructura de fichero

* Código del nodo cliente y nodo servidor: /contiki/examples/experimentosTFM
* Código del router de borde: /contiki/examples/ipv6/rpl-border-router
* Archivos de posición para su uso con Mobility: /contiki/examples/experimentosTFM
* Archivos de simulación de COOJA:  /contiki/tools/cooja/

## Por defecto el plugin Mobility no estara habilitado

![sin mobility](https://drive.google.com/uc?export=view&id=15fIZKkE-3T69AHYXDg2DE0h682nBg_st)

Para solucionar este problema bastara con habilitarlo

![mobility](https://drive.google.com/uc?export=view&id=15mMxrkSxNaDDNkMjlicgC27936Kbq_hm)

Al cerrar COOJA y volver a iniciar, estará ya instalado

![pruebamo](https://drive.google.com/uc?export=view&id=15sNjNteglSCHVgo5ibyg4_yuI2vrxMIg)
