9.7.1
correct is:
System.out.println(f.i);
System.out.println(f.s);
f.imethod();
f.smethod();
System.out.println(F.s);
F.smethod();
9.7.2
void main之前和int factorIcal之前可以添加static
9.7.3
---1---不可以从静态变量里调用实例方法或者引用实例变量
---2---可以从实例方法中调用静态方法或引用一个静态变量
---3---代码错在method2是一个静态方法，c是一个实例变量，不可以从静态方法中调用或引用一个实例变量
