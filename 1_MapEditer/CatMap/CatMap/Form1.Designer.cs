namespace CatMap
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.CatMap = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.tbxWidth = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tbxHeight = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.btnMix = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.tbxIn_Cut = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.tbxOut1_Cut = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.tbxOut2_Cut = new System.Windows.Forms.TextBox();
            this.tbxIn1_Mix = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.tbxIn2_Mix = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.tbxOut_Mix = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // CatMap
            // 
            this.CatMap.Location = new System.Drawing.Point(168, 29);
            this.CatMap.Name = "CatMap";
            this.CatMap.Size = new System.Drawing.Size(88, 60);
            this.CatMap.TabIndex = 0;
            this.CatMap.Text = "Cut";
            this.CatMap.UseVisualStyleBackColor = true;
            this.CatMap.Click += new System.EventHandler(this.CatMap_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 126);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(90, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Input: \"InOut\\";
            // 
            // tbxWidth
            // 
            this.tbxWidth.Location = new System.Drawing.Point(72, 29);
            this.tbxWidth.Name = "tbxWidth";
            this.tbxWidth.Size = new System.Drawing.Size(79, 22);
            this.tbxWidth.TabIndex = 3;
            this.tbxWidth.Text = "16";
            this.tbxWidth.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbxWidth_KeyPress);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(78, 17);
            this.label2.TabIndex = 4;
            this.label2.Text = "Size to cut:";
            // 
            // tbxHeight
            // 
            this.tbxHeight.Location = new System.Drawing.Point(72, 67);
            this.tbxHeight.Name = "tbxHeight";
            this.tbxHeight.Size = new System.Drawing.Size(79, 22);
            this.tbxHeight.TabIndex = 5;
            this.tbxHeight.Text = "16";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 32);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 17);
            this.label3.TabIndex = 6;
            this.label3.Text = "Width";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 70);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(49, 17);
            this.label4.TabIndex = 7;
            this.label4.Text = "Height";
            // 
            // btnMix
            // 
            this.btnMix.Location = new System.Drawing.Point(317, 32);
            this.btnMix.Name = "btnMix";
            this.btnMix.Size = new System.Drawing.Size(269, 55);
            this.btnMix.TabIndex = 8;
            this.btnMix.Text = "Mix";
            this.btnMix.UseVisualStyleBackColor = true;
            this.btnMix.Click += new System.EventHandler(this.btnMix_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(12, 189);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(102, 17);
            this.label7.TabIndex = 12;
            this.label7.Text = "Output: \"InOut\\";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(11, 156);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(102, 17);
            this.label8.TabIndex = 11;
            this.label8.Text = "Output: \"InOut\\";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(314, 186);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(102, 17);
            this.label9.TabIndex = 13;
            this.label9.Text = "Output: \"InOut\\";
            // 
            // tbxIn_Cut
            // 
            this.tbxIn_Cut.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tbxIn_Cut.Location = new System.Drawing.Point(108, 124);
            this.tbxIn_Cut.Name = "tbxIn_Cut";
            this.tbxIn_Cut.Size = new System.Drawing.Size(98, 22);
            this.tbxIn_Cut.TabIndex = 14;
            this.tbxIn_Cut.Text = "map";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(212, 127);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(41, 17);
            this.label10.TabIndex = 15;
            this.label10.Text = ".png\"";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(210, 157);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(41, 17);
            this.label11.TabIndex = 16;
            this.label11.Text = ".png\"";
            // 
            // tbxOut1_Cut
            // 
            this.tbxOut1_Cut.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tbxOut1_Cut.Location = new System.Drawing.Point(120, 152);
            this.tbxOut1_Cut.Name = "tbxOut1_Cut";
            this.tbxOut1_Cut.Size = new System.Drawing.Size(87, 22);
            this.tbxOut1_Cut.TabIndex = 17;
            this.tbxOut1_Cut.Text = "tileSet";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(212, 192);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(31, 17);
            this.label12.TabIndex = 18;
            this.label12.Text = ".txt\"";
            // 
            // tbxOut2_Cut
            // 
            this.tbxOut2_Cut.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tbxOut2_Cut.Location = new System.Drawing.Point(123, 187);
            this.tbxOut2_Cut.Name = "tbxOut2_Cut";
            this.tbxOut2_Cut.Size = new System.Drawing.Size(84, 22);
            this.tbxOut2_Cut.TabIndex = 19;
            this.tbxOut2_Cut.Text = "matrix";
            // 
            // tbxIn1_Mix
            // 
            this.tbxIn1_Mix.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tbxIn1_Mix.Location = new System.Drawing.Point(410, 126);
            this.tbxIn1_Mix.Name = "tbxIn1_Mix";
            this.tbxIn1_Mix.Size = new System.Drawing.Size(140, 22);
            this.tbxIn1_Mix.TabIndex = 22;
            this.tbxIn1_Mix.Text = "tileSet";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(556, 126);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(41, 17);
            this.label13.TabIndex = 21;
            this.label13.Text = ".png\"";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(314, 128);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(90, 17);
            this.label14.TabIndex = 20;
            this.label14.Text = "Input: \"InOut\\";
            // 
            // tbxIn2_Mix
            // 
            this.tbxIn2_Mix.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tbxIn2_Mix.Location = new System.Drawing.Point(410, 156);
            this.tbxIn2_Mix.Name = "tbxIn2_Mix";
            this.tbxIn2_Mix.Size = new System.Drawing.Size(140, 22);
            this.tbxIn2_Mix.TabIndex = 25;
            this.tbxIn2_Mix.Text = "matrix";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(556, 157);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(31, 17);
            this.label5.TabIndex = 24;
            this.label5.Text = ".txt\"";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(314, 158);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(90, 17);
            this.label6.TabIndex = 23;
            this.label6.Text = "Input: \"InOut\\";
            // 
            // tbxOut_Mix
            // 
            this.tbxOut_Mix.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tbxOut_Mix.Location = new System.Drawing.Point(426, 184);
            this.tbxOut_Mix.Name = "tbxOut_Mix";
            this.tbxOut_Mix.Size = new System.Drawing.Size(124, 22);
            this.tbxOut_Mix.TabIndex = 26;
            this.tbxOut_Mix.Text = "gameMap_Mixed";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(556, 187);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(41, 17);
            this.label15.TabIndex = 27;
            this.label15.Text = ".png\"";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(618, 223);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.tbxOut_Mix);
            this.Controls.Add(this.tbxIn2_Mix);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.tbxIn1_Mix);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.tbxOut2_Cut);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.tbxOut1_Cut);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.tbxIn_Cut);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.btnMix);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.tbxHeight);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tbxWidth);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.CatMap);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button CatMap;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbxWidth;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tbxHeight;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btnMix;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox tbxIn_Cut;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox tbxOut1_Cut;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox tbxOut2_Cut;
        private System.Windows.Forms.TextBox tbxIn1_Mix;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox tbxIn2_Mix;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox tbxOut_Mix;
        private System.Windows.Forms.Label label15;
    }
}

