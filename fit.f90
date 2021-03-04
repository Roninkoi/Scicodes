subroutine fitline(xdata, ydata, n, a, b)
  real(rk), allocatable :: xdata(:)
  real(rk), allocatable :: ydata(:)

  integer :: n, i
  real(rk) :: a, b, d, sx2, sx, sy, sxy

  d = 0.0
  sx2 = 0.0
  sx = 0.0
  sy = 0.0
  sxy = 0.0

  i = 1
  do while (i <= n)
     sx2 = sx2 + xdata(i)**2

     sx = sx + xdata(i)
     sy = sy + ydata(i)
     sxy = sxy + xdata(i) * ydata(i)

     i = i + 1
  end do

  d = n*sx2 - sx**2

  a = (sx2 * sy - sx * sxy) / d
  b = (n * sxy - sx * sy) / d
end subroutine fitline
