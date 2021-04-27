c *********************************************************************
c * DATA DE CRIACAO  : 01/09/2018                                     *
c * DATA DE MODIFICAO: 00/00/0000                                     *
c * ----------------------------------------------------------------- *
c * heat: Programa de volume finitos para equacao do calor 1d         *
c * ----------------------------------------------------------------- *
c * ----------------------------------------------------------------- *
c * OBS:                                                              *
c * ----------------------------------------------------------------- *
c *********************************************************************      
      program heat
      implicit none
      include 'Time.fi'
      character(len=80) nameOut, dum, name
      real(8) lComp,dx,dt,ccv(2),t,temp0,h(2),prop(3)      
      integer nCells,nPoints,nDiv,i,j,cc(2),nStep
      integer, dimension(:,:), allocatable :: cells
      real(8), dimension(:), allocatable :: b,x,xc,cellTemp,nodeTemp,
     .                                      k,ro,cp,sQ
      real(8), dimension(:), allocatable :: ye
      real(8), dimension(:,:), allocatable :: a,aux
      integer nin  /11/
      integer nout1 /12/,nout2 /13/, nout3 /14/
c .....................................................................
c
c ...
      timeSolver = 0.d0
      timeSist   = 0.d0
      timeWres   = 0.d0
c .....................................................................
c
c ...
      call readfile(lComp,nDiv,dt,nStep,cc,ccv,h,temp0,prop,nameOut,nin)
c .....................................................................
c
c ....
      nCells  = nDiv
      nPoints = nDiv + 1
c .....................................................................
c
c ...
      allocate(b(nCells)       , x(nPoints), xc(nCells)
     1       , cellTemp(nCells), nodeTemp(nPoints)
     2       , k(nCells)       , ro(nCells), cp(nCells)
     3       , a(nCells,3)     , aux(nCells,2)
     4       , cells(2,nCells) , sQ(nCells), ye(nPoints))
c .....................................................................
c
c .... gera o gride
      call grid(x,xc,cells,lComp,dx,nCells,nPoints,nDiv)  
c ....................................................................
c
c ...
      t                  = 0.d0
      k(1:nCells)        = prop(1)
      ro(1:nCells)       = prop(2)
      cp(1:nCells)       = prop(3)
      cellTemp(1:nCells) = temp0
      sQ(1:nCells)       = 0.d0
c ....................................................................      
c
c ...
      name = trim(nameOut) // '_cell.fortran'
      open(unit=nout1,FILE=name)
      name = trim(nameOut) // '_node.fortran'
      open(unit=nout2,FILE=name)
c      name = trim(nameOut) // '_ex.out'
c      open(unit=nout3,FILE=name)
c ....................................................................
c
c ...
      call nodalInterpol(cells,cc,ccv,cellTemp,nodeTemp,nCells
     .                  ,nPoints)
c ...................................................................
c
c ...  escrita da coordenada do centroide
      time0 = get_wtime()
      call res(0,0.d0,xc,nCells,nout1)
      call res(0,0.d0,x,nPoints,nout2)
c      call res(0,0.d0,x,nPoints,nout3)
      timeWres = timeWres + get_wtime() - time0
c ...................................................................
c
c ...
      call solExt(x,ye,t,dsqrt(k(1)/ro(1)*cp(1)),lComp,nPoints)
c ...................................................................
c 
c ...  escrita da temperatura inicial
      time0 = get_wtime()
      call res(0,0.d0,cellTemp,nCells ,nout1)
      call res(0,0.d0,nodeTemp,nPoints,nout2)
c      call res(0,0.d0,ye      ,nPoints,nout3)
c      call derr(ye,nodeTemp,nPoints)
      timeWres = timeWres + get_wtime() - time0
c ...................................................................
c
c ...
      write(*,'(20a)')'Running ...'
c ...................................................................
c
c ...
      do j = 1, nStep
c
c ... 
c       write(*,'(a10,1x,i9)')'Step :', j
c       write(*,'(a10,1x,f9.4)')'Time(s) :',t
        t = t + dt
c ...................................................................
c
c ...
c       write(*,*)'Assembly of the matrix system :'
        time0 = get_wtime()
        call montaSistema(a,b,cellTemp,sQ,k,ro,cp,dt,cc,ccv,h,dx,nCells)
        timeSist = timeSist + get_wtime() - time0
c ...................................................................     

c ... Ax = B
c       write(*,*)'Ax=b :'
        time0 = get_wtime()
        call tdma_solver2(a(1,1),a(1,2),a(1,3),b,cellTemp
     .                   ,aux(1,1),aux(1,2),nCells)
        timeSolver = timeSolver + get_wtime() - time0
c ...................................................................
c
c ...
        call nodalInterpol(cells,cc,ccv,cellTemp,nodeTemp,nCells
     .                    ,nPoints)
c ...................................................................
c 
c ...
c       call solExt(x,ye,t,dsqrt(k(1)/ro(1)*cp(1)),lComp,nPoints)
c ...................................................................
c
c ... 
c       write(*,*)'Write res :'
        time0 = get_wtime()
        call res(j,t,cellTemp,nCells ,nout1)
        call res(j,t,nodeTemp,nPoints,nout2)
c        call res(j,t,ye      ,nPoints,nout3)
c        call derr(ye,nodeTemp,nPoints)
        timeWres = timeWres + get_wtime() - time0
c ...................................................................
      enddo
c ...................................................................
c
c ...
      write(*,'(20a)')'done.'
c ...................................................................
c
c ...
      write(*,10)timeSist,timeSolver,timeWres
c ...................................................................
c
c ...
      deallocate(b,x,xc
     1          ,cellTemp,nodeTemp
     2          ,k       ,ro      ,cp
     3          ,a       ,aux
     4          ,cells   ,sQ      ,ye)
c ...................................................................
c
c ...
      close(nout1)
      close(nout2)
c      close(nout3)
c ......................................................................
      stop
   10 format(/,'Time Sist(s)   : ', f10.4,/
     1        ,'Time Solver(s) : ', f10.4,/
     2        ,'Time Wres(s)   : ', f10.4,/)
      end
c *********************************************************************
