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
using Trivia_Client.Code;
using Trivia_Client.Pages;
using Json = System.Text.Json;

namespace Trivia_Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 
    public abstract record Response(uint status);
    public record ErrorResponse(uint status, string message) : Response(status);
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            mainFrame.Content = new Pages.Login();

            Response response = new ErrorResponse(3, "s");
            var jsonString = Json.JsonSerializer.Serialize(ErrorResponse(response));
            Console.WriteLine(jsonString);
        }
    }
}
