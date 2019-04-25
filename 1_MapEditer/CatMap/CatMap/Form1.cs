using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CatMap
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public int width = 16, height = 16;

        private void CatMap_Click(object sender, EventArgs e)
        {
            width = 16; height = 16;
            int imgWidth, imgHeight;
            string matrixLine = "";
            Int32.TryParse(tbxWidth.Text,out width);
            Int32.TryParse(tbxHeight.Text, out height);
            
            
            //Load image
            Image img = Image.FromFile(@"InOut\map.png");
            if (img == null)
                MessageBox.Show(@"Missing Inout\map.png");
            imgWidth = img.Width;
            imgHeight = img.Height;

            if(File.Exists(@"InOut\matrix.txt"))
            {
                File.Delete(@"InOut\matrix.txt");
            }
            if (File.Exists(@"InOut\matrix_tmp.txt"))
            {
                File.Delete(@"InOut\matrix_tmp.txt");
            }

            //Create list
            List<Bitmap> lstTile = new List<Bitmap>();
            Bitmap cloned;
            Bitmap tileSet=null;
            Rectangle rect;
            //Crop image
            for (int y=0;y<imgHeight;y+=height)
            {
                matrixLine = "";
                for(int x=0;x<imgWidth;x+=width)
                {
                    rect = new Rectangle(x, y, width, height);
                    cloned = new Bitmap(img).Clone(rect, img.PixelFormat);
                    bool isExited = false;
                    for (int i = 0; i < lstTile.Count; i++)
                    {
                        //pictureBox1.Image = cloned;
                        //pictureBox2.Image = lstTile[i];
                        
                        //So sanh xem cái hình vừa clone có tồn tại chưa
                        if(Equals(cloned,lstTile[i]))//Nếu có rồi thì...
                        {
                            isExited = true;
                            //matrixLine += (i) + " ";
                            matrixLine += (i+1) + " "; // Viết i+1 vô ma trận map
                            //(chú ý là ma trận bắt đầu từ 1 chứ k phải từ 0 như list) do số 0 mình chừa cho mục đích k có gì
                        }

                    }
                    if(!isExited)//Nếu cái hình vừa so sánh chưa có thì...
                    {
                        lstTile.Add(cloned);//Thêm nó vào list
                        //matrixLine +=lstTile.Count-1+ " ";
                        matrixLine += lstTile.Count + " ";//Viết số của nó vô ma trận 
                        //add vo bitmap
                        tileSet =AppendBitmap(tileSet, cloned, 0);
                    }
                    //MessageBox.Show("a");
                    GC.Collect();
                }
                WriteLineToFileWithUTF8(@"InOut\matrix_tmp.txt", matrixLine);
                
            }
            //First line
            string line;
            WriteLineToFileWithUTF8(@"InOut\matrix.txt", lstTile.Count.ToString()+" "+imgHeight/height+" "+imgWidth/width);
            System.IO.StreamReader file = new System.IO.StreamReader(@"InOut\matrix_tmp.txt");
            while ((line = file.ReadLine()) != null)
            {
                WriteLineToFileWithUTF8(@"InOut\matrix.txt", line);
            }
            file.Close();

            if (File.Exists(@"InOut\matrix_tmp.txt"))
            {
                File.Delete(@"InOut\matrix_tmp.txt");
            }
            
            MessageBox.Show("Done!");

            //Save tileSet
            if (File.Exists(@"InOut\tileSet.png"))
            {
                File.Delete(@"InOut\tileSet.png");
            }
            tileSet.Save(@"InOut\tileSet.png", System.Drawing.Imaging.ImageFormat.Png);


        }

        #region Mix
        private void btnMix_Click(object sender, EventArgs e)
        {
            //Khoi tao bmp luu map
            Bitmap tile;
            Bitmap gameMap=null;
            Rectangle rect;

            width = 16; height = 16;
            string line = "";
            
            //Lay w h cua 1 tile 
            Int32.TryParse(tbxWidth.Text, out width);
            Int32.TryParse(tbxHeight.Text, out height);

            //Load tile map image
            Image img = Image.FromFile(@"InOut\tileSet.png");
            if (img == null)
            {
                MessageBox.Show(@"Missing Inout\tileSet.png");
                return;
            }
              
            //Load matrix
            if (!File.Exists(@"InOut\matrix.txt"))
            {
                MessageBox.Show(@"Missing Inout\matrix");
                return;
            }
            System.IO.StreamReader file = new System.IO.StreamReader(@"InOut\matrix.txt");
            line = file.ReadLine();//First line

            string[] row;
            int lineCount = 0;
            while ((line = file.ReadLine()) != null)
            {
                //Xu ly
                //Cat line ra ma tran dong
                row=line.Split(' ');//dư 1 phần
                for(int i=0;i<row.Count()-1;i++)
                {
                    //Lay so thu tu img
                    int numPieceOfMap = 0;
                    Int32.TryParse(row[i], out numPieceOfMap);
                    if(numPieceOfMap!=0)
                    {
                        //Lay tile
                        rect = new Rectangle((numPieceOfMap - 1) * width, 0, width, height);
                        tile = new Bitmap(img).Clone(rect, img.PixelFormat);
                        //Them vao map
                        gameMap = AppendBitmapAt(gameMap, tile, i * width, lineCount * height);

                        GC.Collect();
                    }
                }
                lineCount++;
                
            }
            file.Close();
            //Save file
            gameMap.Save(@"InOut\gameMap_Mixed.png", System.Drawing.Imaging.ImageFormat.Png);
            MessageBox.Show("Done!");

        }

        #endregion

        #region Function

        public Bitmap AppendBitmap(Bitmap source, Bitmap target, int spacing)
        {
            if (source != null && target != null)
            {
                int w = source.Width + target.Width + spacing;
                int h = Math.Max(source.Height, target.Height);
                
                Bitmap bmp = new Bitmap(w, h);

                using (Graphics g = Graphics.FromImage(bmp))
                {
                    g.DrawImage(source, 0, 0); //Draw image from a point
                    g.DrawImage(target,  source.Width + spacing,0);//Draw image from a point
                }

                return bmp;
            }
            else if (source == null)
            {
                return target;
            }
            else
                return source;
        }
        //
        public Bitmap AppendBitmapAt(Bitmap source, Bitmap target, int xPos,int yPos)
        {
            if (source != null && target != null)
            {
                int w, h;
                if (xPos + target.Width > source.Width)
                    w = xPos + target.Width;
                else
                    w = source.Width;
                if (yPos + target.Height > source.Height)
                    h = yPos + target.Height;
                else
                    h = source.Height;
                Bitmap bmp = new Bitmap(w, h);

                using (Graphics g = Graphics.FromImage(bmp))
                {
                    g.DrawImage(source, 0, 0); //Draw image from a point
                    g.DrawImage(target, xPos,yPos);//Draw image from a point
                }

                return bmp;
            }
            else if (source == null)
            {
                return target;
            }
            else
                return source;
        }
        private bool Equals(Bitmap bmp1, Bitmap bmp2)
        {
            
            if (!bmp1.Size.Equals(bmp2.Size))
            {
                return false;
            }
            for (int x = 0; x < bmp1.Width; ++x)
            {
                for (int y = 0; y < bmp1.Height; ++y)
                {
                    if (bmp1.GetPixel(x, y) != bmp2.GetPixel(x, y))
                    {
                        return false;
                    }
                }
            }
            return true;
            
        }
        private void WriteLineToFileWithUTF8(string filePath, string txt)
        {
            using (FileStream fs = new FileStream(filePath, FileMode.Append))
            {
                using (StreamWriter writer = new StreamWriter(fs, Encoding.UTF8))
                {
                    writer.WriteLine(txt);
                }
            }
        }
        private void tbxWidth_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }
    }
    #endregion
}
