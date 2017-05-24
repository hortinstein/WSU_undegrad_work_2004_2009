int kcinth()
{
   ushort segment, offset, a;
   segment = running->uss; offset = running->usp;

   a = get_word(segment, offset + 2*13);

   printf("\nkcinth: your syscall # = %d\n", a);
}
