void processCommand()
{
  float xx=pos_x;
  float yy=pos_y;
  float zz=pos_z;
 
  char *ptr=buffer;
  while(ptr && ptr<buffer+sofar) {
    ptr=strchr(ptr,' ')+1;
    switch(*ptr) {
    case 'x': case 'X': xx=atof(ptr+1); break;
    case 'y': case 'Y': yy=atof(ptr+1); break;
    case 'z': case 'Z': zz=atof(ptr+1); break;
    default: ptr=0; break;
    }
  }
//  lcdPrint(xx,yy,zz);
  jog(xx,yy,zz);
  targetX=pos_x/1000;
  targetY=pos_y/1000;
  targetZ=pos_z/1000;
}



