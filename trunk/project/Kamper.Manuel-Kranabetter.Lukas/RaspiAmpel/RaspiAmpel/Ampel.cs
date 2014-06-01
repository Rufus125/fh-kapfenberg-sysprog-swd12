using System;
using System.Timers;
using System.Collections.Generic;
using LibPiGpio;

namespace RaspiAmpel
{
    public class Ampel
    {
        //diverse Flags
        internal static bool onoffRequest = false;
        internal static bool ampelAktiv = false;
        internal static bool inPhase = false;
        internal static bool ampelAuto = true;
        internal static bool walkerA = false; //re-li
        internal static bool waitWalkerA = false;
        internal static bool walkerB = false; //ob-un
        internal static bool waitWalkerB = false;

        //Timer als Heartbeat
        private static Timer heartbeat;

        //diverse Zähler
        internal static int heartbeatCount = 0;
        internal static int phaseTimer = 0;
        internal static int phaseNr = 0;

        //Zeitpunkte für Phasenwechsel - siehe "Programmablauf.xlsx"
        internal static int[] zeitpunkte = new int[] { 5, 2, 10, 6, 4, 6, 5, 5, 2, 10, 6, 4, 6, 5 };

        //Nummern der GPIOs für out und in - siehe "Ampel-GPIO Zuweisung.xlsx"
        internal static int[] gpioOut = new int[] { 17, 18, 22, 23, 24, 25, 8, 9, 4, 7 };
        internal static int[] gpioIn = new int[] { 10, 11, 27 };

        private static void Main()
        {
            //Heartbeat Frequenz festlegen, EventHandler zuweisen und aktivieren
            heartbeat = new Timer(1000); //Heartbeat im Sekundentakt
            heartbeat.Elapsed += new ElapsedEventHandler(heartbeat_Elapsed);
            heartbeat.Enabled = true;

            //Programmbeschreibung ausgeben (Header)
            Console.Clear();
            Console.WriteLine("RaspiAmpel v0.4 - Build 20.05.2014");
            Console.WriteLine("by Manuel Kamper & Lukas Kranabetter");
            Console.WriteLine("====================================");
            Console.WriteLine("Keys: s (on/off); i (status infos); x (shutdown); h (switch modes)");
            Console.WriteLine("p (poll next phase); f+g (request pedestrian lights)");

            GpioControl.InitGpio(); //instanziert alle benötigten GPIOs
            
            AppControl.CheckForKey(); //Steuerbefehle
        }

        /// <summary>
        /// Wird bei jedem Heartbeat ausgeführt
        /// .) betreibt die Ampel
        /// .) Löscht Messages nach 5 Anzeigesekunden
        /// .) Zeigt Heartbeat-Infos an
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private static void heartbeat_Elapsed(object sender, ElapsedEventArgs e)
        {
            //starten und beenden der Ampel
            if (onoffRequest)
            {
                if(ampelAktiv) //sicheres ausschalten; erst wenn alle Ampeln rot sind
                {
                    if (phaseNr == 0 || phaseNr == 7)
                    {
                        if (Ampel.inPhase)
                        {
                            Ampel.phaseNr = 0;
                            Ampel.inPhase = false;
                        }
                        ampelAktiv = false;
                        onoffRequest = false;
                    }
                }
                else //einschalten
                {
                    ampelAktiv = true;
                    onoffRequest = false;
                }
            }

            //der eigentliche Ampelbetrieb
            if (ampelAktiv)
            {
                GpioControl.nextPhase();
                AmpelBitmuster.AmpelBit(Ampel.phaseNr);
            }
            else
            {
                GpioControl.GelbBlinken();
            }

            //Message nach 5 Sekunden Anzeigedauer löschen
            if (AppControl.lastMessage == heartbeatCount - 5 && AppControl.lastMessage != 0)
            {
                AppControl.lastMessage = 0;
                AppControl.ResetLine(1, 6);
            }

            //Info über aktuellen Heartbeat ausgeben
            if (heartbeatCount == int.MaxValue) { heartbeatCount = 0; }; //damit wir nach 68 Jahren Ampelbetrieb nicht wo hin kommen wo wir nichts zu suchen haben
            heartbeatCount++;
            AppControl.OverwriteLine(1, 8, "♥ " + heartbeatCount.ToString() + " " + (ampelAktiv ? "►" : "") + "; phase #" + phaseNr);
        }
    }
}