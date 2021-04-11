# VolumeFinito

Solução do equação do calor utilizando o método dos volumes finitos para problemas unidimensionais. Objetivo é a comparação de uma implementação simples de volume finitos em diversas linguagem diferentes.

# liguagens de implementação
* Fortran
* Python (puro)
* Python (numpy)

# Resultados

## Temperatura prescrita

* Condições de contorno
<img src="https://render.githubusercontent.com/render/math?math=T(0 ,t) = 10">
<img src="https://render.githubusercontent.com/render/math?math=T(50,t) = 30">

* Condição inicial
<img src="https://render.githubusercontent.com/render/math?math=T(x,0) = 20">

![Temperatura](https://github.com/HenriqueCCdA/VolumeFinito/blob/master/gifs/temperatura.gif) 

## Fluxo prescrito

* Condições de contorno
<img src="https://render.githubusercontent.com/render/math?math=T(0 ,t) = 10">
<img src="https://render.githubusercontent.com/render/math?math=q_n(50,t) = -1.5">

* Condição inicial
<img src="https://render.githubusercontent.com/render/math?math=T(x,0) = 20">

![fluxo](https://github.com/HenriqueCCdA/VolumeFinito/blob/master/gifs/fluxo.gif) 


## Fluxo convectivo ( Lei de resfriamento de Newton )

* Condições de contorno
<img src="https://render.githubusercontent.com/render/math?math=T(0 ,t) = 10">
<img src="https://render.githubusercontent.com/render/math?math=q_n(50, t) = 1.0 ( T - 30 ) ">

* Condição inicial
<img src="https://render.githubusercontent.com/render/math?math=T(x,0) = 20">

![newton](https://github.com/HenriqueCCdA/VolumeFinito/blob/master/gifs/newton.gif) 


# Referencia

<a href="http://ftp.demec.ufpr.br/disciplinas/TM702/Versteeg_Malalasekera_2ed.pdf"> Versteeg, H., Malalasekera, W. An Introduction to Computational Fluid Dynamics: The Finite Volume Method. 2 ed. , Pearson Education Limited, 2007</a>
