! fit with errors
subroutine fitlinesigma(xdata, ydata, n, sigma, a, b, sa, sb)
  real(rk), allocatable :: xdata(:)
  real(rk), allocatable :: ydata(:)

  integer :: n, i
  real(rk) :: a, b, sa, sb
  real(rk) :: d, sx2, sx, sy, sxy, ss, s2, sigma

  s2 = sigma**2

  d = 0.0
  sx2 = 0.0
  sx = 0.0
  sy = 0.0
  sxy = 0.0
  ss = 0.0

  i = 1
  do while (i <= n)
     sx2 = sx2 + (xdata(i)**2)/s2

     ss = ss + 1.0/s2

     sx = sx + xdata(i)/s2
     sy = sy + ydata(i)/s2
     sxy = sxy + (xdata(i) * ydata(i))/s2

     i = i + 1
  end do

  d = ss*sx2 - sx**2

  a = (sx2 * sy - sx * sxy) / d
  b = (ss * sxy - sx * sy) / d

  sa = sqrt((sx2) / d)
  sb = sqrt((ss) / d)
end subroutine fitlinesigma
