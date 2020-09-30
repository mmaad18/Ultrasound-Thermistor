using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace NTCKalkulator
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            if (Validator())
            {
                calculate();
            }
        }

        double L(double resistance)
        {
            return Math.Log(resistance);
        }

        double Y(double temperature)
        {
            return 1 / temperature;
        }

        void calculate()
        {
            double R1 = Convert.ToDouble(R1box.Text);
            double R2 = Convert.ToDouble(R2box.Text);
            double R3 = Convert.ToDouble(R3box.Text);

            double T1 = Convert.ToDouble(T1box.Text) + 273.15;
            double T2 = Convert.ToDouble(T2box.Text) + 273.15;
            double T3 = Convert.ToDouble(T3box.Text) + 273.15;

            double L1 = L(R1);
            double L2 = L(R2);
            double L3 = L(R3);

            double Y1 = Y(T1);
            double Y2 = Y(T2);
            double Y3 = Y(T3);

            double G2 = (Y2 - Y1) / (L2 - L1);

            double G3 = (Y3 - Y1) / (L3 - L1);

            double C = ((G3 - G2) / (L3 - L2)) * Math.Pow((L1 + L2 + L3), -1);

            double B = G2 - C * (Math.Pow(L1, 2) + L1 * L2 + Math.Pow(L2, 2));

            double A = Y1 - (B + C * Math.Pow(L1, 2)) * L1;

            Abox.Text = A.ToString();
            Bbox.Text = B.ToString();
            Cbox.Text = C.ToString();
        }

        bool Validator()
        {
            double R1, R2, R3, T1, T2, T3;

            if(IsInitialized && NotEmpty())
            {
                try
                {
                    R1 = Convert.ToDouble(R1box.Text);
                    R2 = Convert.ToDouble(R2box.Text);
                    R3 = Convert.ToDouble(R3box.Text);

                    T1 = Convert.ToDouble(T1box.Text);
                    T2 = Convert.ToDouble(T2box.Text);
                    T3 = Convert.ToDouble(T3box.Text);

                    return true;
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Melding: " + ex + "\n");

                    Abox.Text = "Error";
                    Bbox.Text = "Error";
                    Cbox.Text = "Error";

                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        bool NotEmpty()
        {
            if(R1box.Text != "" && R2box.Text != "" && R3box.Text != "" && T1box.Text != "" && T2box.Text != "" && T3box.Text != "")
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        private void R1box_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (Validator())
            {
                calculate();
            }
        }

        private void R2box_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (Validator())
            {
                calculate();
            }
        }

        private void R3box_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (Validator())
            {
                calculate();
            }
        }

        private void T1box_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (Validator())
            {
                calculate();
            }
        }

        private void T2box_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (Validator())
            {
                calculate();
            }
        }

        private void T3box_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (Validator())
            {
                calculate();
            }
        }
    }
}
