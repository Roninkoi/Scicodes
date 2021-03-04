subroutine sort(xdata, ydata, n) ! sort by x inc
  real(rk), allocatable :: xdata(:)
  real(rk), allocatable :: ydata(:)

  integer :: n, i, j, mini

  real(rk) :: minx, tx, ty

  i = 1
  do while (i <= n)
     minx = xdata(i)
     mini = i

     j = i + 1
     do while (j <= n)
        tx = xdata(j)

        if (tx < minx) then
           minx = tx
           mini = j
        end if

        j = j + 1
     end do

     tx = xdata(i)
     ty = ydata(i)

     xdata(i) = xdata(mini)
     ydata(i) = ydata(mini)

     xdata(mini) = tx
     ydata(mini) = ty

     i = i + 1
  end do
end subroutine sort
