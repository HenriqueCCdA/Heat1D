c *********************************************************************
      subroutine solExt(x,y,t,alfa,l,n)
      implicit none
      integer n,i
      real*8 x(*),y(*),t,alfa,l
      real*8 func1
c ...
      do i = 1, n
        y(i) = func1(x(i),t,alfa,l,100)
      enddo
c .....................................................................
      return
      end 
c *********************************************************************
      real(8) function func1(x,t,alfa,l,n)
      implicit none
      integer i,n
      real(8) x,t,PI,tmp,ex,a,l,alfa
      PI =4.d0*DATAN(1.d0)
      tmp = 0.0
      do i = 1, n, 2        
        ex = (i*PI*alfa/l)**2
        a  = i*PI/l
        tmp = tmp + (1.d0/i)*dexp(-ex*t)*dsin(a*x)
      enddo
      func1 = tmp*80.d0/PI
      return
      end
c *********************************************************************
c
c *********************************************************************
      subroutine derr(ye,y,n)
      implicit none
      integer i,n
      real(8) ye(*),y(*),tmp0,tmp1,er
      tmp0 = 0.d0
      tmp1 = 0.d0
      do i = 1, n
        tmp0  = tmp0 + (ye(i) - y(i))**2
        tmp1 = tmp1 + ye(i)**2
      enddo
      er = dsqrt(tmp0)/ dsqrt(tmp1)
      print*,er
      return
      end