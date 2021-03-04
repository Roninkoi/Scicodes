! Monte Carlo fit
subroutine fitlinemc(xdata, ydata, n, sigma, a, b, sa, sb, ag, bg)
  real(rk), allocatable :: xdata(:)
  real(rk), allocatable :: ydata(:)
  real(rk), allocatable :: sigma(:)

  integer :: n, i, ii, sn
  real(rk) :: a, b, sa, sb
  real(rk) :: am, bm, pm
  real(rk) :: sq, sql, ra, rb, ag, bg

  a = ag
  b = bg
  sa = 0.0
  sb = 0.0
  sql = 100000000.0

  sn = 1
  am = 0.0
  bm = 0.0

  do ii = 1, 50000000
     sq = 0.0

     !ra = a + (rand() - 0.5) * a * 0.0001
     !rb = b + (rand() - 0.5) * b * 0.0001
     ra = normrand(a, sqrt(sa))
     rb = normrand(b, sqrt(sb))

     i = 1
     do while (i <= n)
        sq = sq + (normrand(ydata(i), sigma(i)) - (ra + rb * xdata(i)))**2 / (sigma(i)**2)
        i = i + 1
     end do

     if (sq < sql) then
        a = ra
        b = rb

        sn = sn + 1

        pm = am
        am = am + (a - am) / sn
        sa = sa + ((a - pm) * (a - am) - sa) / sn

        pm = bm
        bm = bm + (b - bm) / sn
        sb = sb + ((b - pm) * (b - bm) - sb) / sn

        sql = sq
     end if
  end do

  sa = sqrt(sa)
  sb = sqrt(sb)
end subroutine fitlinemc
