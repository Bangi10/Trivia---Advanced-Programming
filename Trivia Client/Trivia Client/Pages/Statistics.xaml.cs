﻿using System;
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

namespace Trivia_Client.Pages
{
    /// <summary>
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Page
    {
        public Statistics()
        {
            InitializeComponent();
        }
        private void MyStats_Click(object sender, RoutedEventArgs e)
        {
            //working but not as axpected
            StatisticsFrame.Content = new MyStats();

            //doesnt work but mabey it could help
            //MyStats myStats = new MyStats();
            //this.Content = myStats;
        }
        private void HighScores_Click(object sender, RoutedEventArgs e)
        {
            //working but not as axpected
            StatisticsFrame.Content = new HighScores();

            //doesnt work but mabey it could help
            //HighScores highScores = new HighScores();
            //this.Content = highScores;
        }
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            NavigationService?.Navigate(new Pages.MainMenu());

        }
    }
}
