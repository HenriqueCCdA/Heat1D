      program heat
      implicit none
      character(len=80) nameOut, dum
      real(8) lComp,dx,dt,ccv(2),t,temp0
      integer nCells,nPoints,nDiv,i,j,cc(2),nStep
      integer, dimension(:,:), allocatable :: cells
      real(8), dimension(:), allocatable :: b,x,xc,temp,k,ro,cp,sQ
      real(8), dimension(:,:), allocatable :: a,aux
      integer nin  /11/
      integer nout /12/
c ...
      nStep = 100
      nDiv  = 10
      lComp = 2.0d-02
      dt    = 2.d0
      t     = 0.d0
      temp0 = 200.d0
c .....................................................................
c
c ...
      call readfile(lComp,nDiv,dt,nStep,cc,ccv,temp0,nameOut,nin)
c .....................................................................
c
c ....
      nCells  = nDiv
      nPoints = nDiv + 1
c .....................................................................
c
c ...
      allocate(b(nCells),x(nPoints),xc(nCells),temp(nCells),k(nCells)
     1        ,ro(nCells),cp(nCells),a(nCells,3),aux(nCells,2)
     2        ,cells(2,nCells),sQ(nCells))
c .....................................................................
c
c .... gera o gride
      call grid(x,xc,cells,lComp,dx,nCells,nPoints,nDiv)  
c ....................................................................
c
c ...
      k(1:nCells)    = 10.d0
      ro(1:nCells)   = 1000.d0
      cp(1:nCells)   = 10000.d0
      temp(1:nCells) = temp0
      sQ(1:nCells)   = 0.d0
c ....................................................................      
c
c ...
      open(unit=nout,FILE=nameOut)
c ....................................................................
c
c ...  escrita da coordenada do centroide
      call res(0,0.d0,xc,nCells,nout)
c ...................................................................
c
c ...  escrita da temperatura inicial
      call res(0,0.d0,temp,nCells,nout)
c ...................................................................
c
c ...
      do j = 1, nStep

c ...
        call montaSistema(a,b,temp,sQ,k,ro,cp,dt,cc,ccv,dx,nCells)
c ...................................................................     

c ... Ax = B
        call tdma_solver2(a(1,1),a(1,2),a(1,3),b,temp
     .                   ,aux(1,1),aux(1,2),nCells)
c ...................................................................
c
c ...
        t = t + dt
        print*,'Time(s)',t
c ...................................................................
c
c ... 
        call res(j,t,temp,nCells,nout)
c ...................................................................
      enddo
c ...................................................................
c
c ...
      deallocate(b,x,xc,temp,k,ro,cp,a,aux)
c ...................................................................
c
c ...
      close(nout)
c ......................................................................
      stop
      end
c *********************************************************************
c
c *********************************************************************
c * DATA DE CRIACAO  : 11/09/2018                                     *
c * DATA DE MODIFICAO: 00/00/0000                                     *
c * ----------------------------------------------------------------- *
c * REAFILE : leitura dos arquivos de dados                           *
c * ----------------------------------------------------------------- *
c * Parametros de entrada:                                            *
c * ----------------------------------------------------------------- *
c * lComp   - nao definido                                            *
c * nDiv    - nao definido                                            *
c * dt      - nao definido                                            *
c * nStep   - nao definido                                            *
c * cc      - nao definido                                            *
c * ccv     - nao definido                                            *
c * temp0   - nao definido                                            *
c * nameOut - nao definido                                            *
c * ----------------------------------------------------------------- *
c * Parametros de saida:                                              *
c * ----------------------------------------------------------------- *
c * lComp   - comprimento da barra                                    *
c * nDiv    - numero de divisoes                                      *
c * dt      - delta                                                   *
c * nStep   - numero de passo de tempo                                *
c * cc      - tipo de condicao de contorno                            *
c         1 - Temperatuta                                             *
c         2 - fluxo                                                   *
c * ccv     - calor da condicao de contorno                           *
c * temp0   - temperatura inicial                                     *
c * nameOut - nome do arquivo de saida                                *
c * ----------------------------------------------------------------- *
c * OBS:                                                              *
c * ----------------------------------------------------------------- *
c *********************************************************************
      subroutine readfile(lComp,nDiv,dt,nStep,cc,ccv,temp0,nameOut,nin)
      implicit none
      character(len=80) nameOut, dum
      integer nDiv,nStep,cc(2),nin
      real*8 dt,ccv(2),lComp,temp0
c ...
      open(unit=nin,file='input.dat')
      read(nin,*) dum,nameOut
      read(nin,*) dum,lComp
      read(nin,*) dum,nDiv
      read(nin,*) dum,dt
      read(nin,*) dum,nStep
      read(nin,*) dum,cc(1),ccv(1)
      read(nin,*) dum,cc(2),ccv(2)
      read(nin,*) dum,temp0      
      close(nin)

      print*,lComp,nDiv,dt,nStep
      print*,cc(1),ccv(1)
      print*,cc(2),ccv(2)
      print*,temp0
      close(nin)
      return
      end
c *********************************************************************
c
c *********************************************************************
c * DATA DE CRIACAO  : 11/09/2018                                     *
c * DATA DE MODIFICAO: 00/00/0000                                     *
c * ----------------------------------------------------------------- *
c * RES : escreve os resultados                                       *
c * ----------------------------------------------------------------- *
c * Parametros de entrada:                                            *
c * ----------------------------------------------------------------- *
c * step - passo de tempo                                             *
c * t    - tempo                                                      *
c * u    - vetor a ser escrito                                        *
c * n    - numero de pontos em u                                      *
c * nout - arquivo de saida                                           *
c * ----------------------------------------------------------------- *
c * Parametros de saida:                                              *
c * ----------------------------------------------------------------- *
c * ----------------------------------------------------------------- *
c * OBS:                                                              *
c * ----------------------------------------------------------------- *
c *********************************************************************
      subroutine res(step,t,u,n,nout)
      implicit none
      integer i,n,step,nout
c ...
      real(8) t,u(*)
c ...  coordenada do centroide    
      write(nout,'(i9,1x,f10.4)',advance='no')step,t
      do i = 1, n
        write(nout,'(1x,f10.4,1x)',advance='no')u(i)
      enddo
c .....................................................................      
      write(nout,*)
      return
      end
c .....................................................................
c *********************************************************************
c
c *********************************************************************
c * DATA DE CRIACAO  : 11/09/2018                                     *
c * DATA DE MODIFICAO: 00/00/0000                                     *
c * ----------------------------------------------------------------- *
c * GRID: gera o gride pontos                                         *
c * ----------------------------------------------------------------- *
c * Parametros de entrada:                                            *
c * ----------------------------------------------------------------- *
c * x    - nao definido                                               *
c * xc   - nao definido                                               *
c * cell - nao definido                                               *
c * comp - comprimento da barra                                       *
c * nPoint - numero de pontos                                         *
c * nDiv   - numero de divisoes (elementos)                           *
c * ----------------------------------------------------------------- *
c * Parametros de saida:                                              *
c * ----------------------------------------------------------------- *
c * x    - cordenada dos pontos                                       *
c * xc   - cordenadas dos centro dos elmentos                         *
c * cell - conectividade nodais do elementos                          *
c * ----------------------------------------------------------------- *
c * OBS:                                                              *
c * ----------------------------------------------------------------- *
c *********************************************************************
      subroutine grid(x,xc,cell,comp,dx,nCell,nPoints,nDiv)  
      implicit none
      integer i,nCell,nPoints,nDiv,cell(2,*)
      real(8) dx,comp
      real(8) x(*),xc(*)
c ... gerando cordenadas nodais
      dx   = comp/nDiv
      x(1) = 0.0d0
      do i = 2, nPoints - 1
        x(i) = x(i-1) + dx
      enddo
      x(nPoints) = comp
c .....................................................................
c
c ... gerando conectividade nodais
      do i = 1, nCell
        cell(1,i) = i 
        cell(2,i) = i + 1
        xc(i)     = (x(i+1)+x(i))*0.5d0
      enddo
c .....................................................................
c
c ...
      return
      end
c .......................................................................            
c *********************************************************************
c
c *********************************************************************
c * DATA DE CRIACAO  : 11/09/2018                                     *
c * DATA DE MODIFICAO: 00/00/0000                                     *
c * ----------------------------------------------------------------- *
c * MONTASISTEMA : monta o sistema AX=B                               *
c * ----------------------------------------------------------------- *
c * Parametros de entrada:                                            *
c * ----------------------------------------------------------------- *
c * a      - nao definido                                             *
c * b      - nao definido                                             *
c * temp   - temperatura do passo anterior                            *
c * sQ     - fonte de calor                                           *
c * k      - coeficiente de conducao termica                          *
c * ro     - massa especidica                                         *
c * cp     - calor espefifico                                         *
c * dt     - delta t                                                  *
c * cc     - tipo de condicao de contorno                             * 
c         1 - Temperatuta                                             *
c         2 - fluxo                                                   *
c * ccv    - valor numerico da condicao de contorno                   *
c * dx     - delta x                                                  *
c * nCells - numero de celulas (elementos)                            * 
c * ----------------------------------------------------------------- *
c * Parametros de saida:                                              *
c * ----------------------------------------------------------------- *
c * a    - matriz de coefientes                                       *
c * b    - vetor b                                                    *
c * ----------------------------------------------------------------- *
c * OBS:                                                              *
c * ----------------------------------------------------------------- *
c *********************************************************************
      subroutine  montaSistema(a,b,temp,sQ,k,ro,cp,dt,cc,ccv,dx,nCells)
      implicit none
      integer cc(2),nCells,i
      real(8) a(nCells,*),b(*),k(*),ro(*),cp(*),temp(*),sQ(*)
      real(8) dt,ccv(2),dx,sP,sU,kf
      real(8) aE,aW,aP0
c ... temperatura prescrita
      if(cc(1) .eq. 1) then
        aP0    = ro(1)*cp(1)*dx/dt
        sU     = (2.0d0*k(1)/dx)*ccv(1)
        sP     = -2.0d0*k(1)/dx
        kf     = (k(1)+k(2))*0.5d0
        aE     = kf/dx
c ... W
        a(1,1) = 0.0
c ... P
        a(1,2) = aP0 + aE - sP
c ... E
        a(1,3) = -aE
c ...
        b(1)   = sU + aP0*temp(1)
c ... fluxo prescrito
      else if(cc(1) .eq. 2) then
        aP0    = ro(1)*cp(1)*dx/dt
        sU     = -ccv(1)
        sP     = 0.0   
        kf     = (k(1)+k(2))*0.5d0
        aE     = kf/dx
c ... W
        a(1,1) = 0.0
c ... P
        a(1,2) = aP0 + aE - sP
c ... E
        a(1,3) = -aE
c ...
        b(1)   = sU + aP0*temp(1)
      endif
c .....................................................................

c ... temperatura prescrita
      if(cc(2) .eq. 1) then
        aP0    = ro(nCells)*cp(nCells)*dx/dt
        sU     = (2.0d0*k(nCells)/dx)*ccv(2)
        sP     = -2.0d0*k(nCells)/dx
        kf     = (k(nCells-1)+k(nCells))*0.5d0
        aW     = kf/dx
c ... W
        a(nCells,1) = -aW
c ... P
        a(nCells,2) = aP0 + aW - sP
c ... E
        a(nCells,3) = 0.0
c ...
        b(nCells)   = sU + aP0*temp(nCells)
c ... fluxo prescrito
      else if(cc(2) .eq. 2) then
        aP0    = ro(nCells)*cp(nCells)*dx/dt
        sU     = -ccv(2)
        sP     = 0.0
        kf     = (k(nCells-1)+k(nCells))*0.5d0
        aE     = kf/dx
c ... W
        a(nCells,1) = -aW
c ... P
        a(nCells,2) = aP0 + aW - sP
c ... E
        a(nCells,3) = 0.0
c ...
        b(nCells)   = sU + aP0*temp(nCells)
      endif
c .....................................................................

c ... loop nas celulas do interios
      do i = 2, nCells -1
        aP0    = ro(i)*cp(i)*dx/dt
c ... w 
        kf = (k(i-1) + k(i))*0.5d0
        aW = kf/dx  
c ...
        kf = (k(i) + k(i+1))*0.5d0
        aE = kf/dx  
c ... 
        a(i,1) = -aW 
        a(i,2) = aP0 + aW + aE 
        a(i,3) = -aE
c ... 
        b(i)   = aP0*temp(i)
      enddo
c .....................................................................
      return
      end
c *********************************************************************
