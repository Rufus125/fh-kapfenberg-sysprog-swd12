using LibPiGpio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace RaspiAmpel
{
    /// <summary>
    /// Controller für GPIOs
    /// by Manuel Kamper
    /// </summary>
    class GpioControl
    {
        /// <summary>
        /// Instanziert alle GPIOs die wir benötigen
        /// </summary>
        internal static void InitGpio()
        {
            AppControl.ResetLine(0, 10); //wird nur für den NOPI Modus benötigt
            RpiGpio.SetOutputPins(Ampel.gpioOut);
            RpiGpio.SetInputPins(Ampel.gpioIn);
        }

        /// <summary>
        /// Schaltet alle GPIO-Out aus
        /// </summary>
        internal static void AlleAus()
        {
            foreach (int gpio in Ampel.gpioOut)
            {
                RpiGpio.Pins[gpio] = false;
            }
        }

        /// <summary>
        /// Alle gelben Ampeln blinken
        /// </summary>
        internal static void GelbBlinken()
        {
            char[] gelbBlink = new char[] { '0', '2', '0', '0', '2', '0', '0', '0', '0', '0' };
            AmpelBitmuster.WriteBitsToGpio(gelbBlink);
        }

        /// <summary>
        /// Triggert die nächste Phase nach Zeitablauf (zeitpunkte) mittels Heartbeat
        /// </summary>
        internal static void nextPhase()
        {
            if (Ampel.phaseTimer == 0) { Ampel.phaseTimer = Ampel.zeitpunkte[Ampel.phaseNr]; Ampel.inPhase = true; }
            Ampel.phaseTimer--;

            if (Ampel.phaseTimer == 0)
            {
                Ampel.phaseNr++;
                if (Ampel.phaseNr == Ampel.zeitpunkte.Length) { Ampel.phaseNr = 0; }
            }
        }

        /// <summary>
        /// Nächste Phase im Handbetrieb anfordern
        /// </summary>
        internal static void RequestPhase()
        {
            if (Ampel.ampelAktiv && !Ampel.ampelAuto)
            {
                //todo: nächste phase anfordern
                System.Console.WriteLine("phase");
            }
        }

        /// <summary>
        /// Anforderungen für die Fußgängerampel
        /// </summary>
        /// <param name="p">1...re-li; 2...ob-un</param>
        internal static void RequestWalker(int p)
        {
            if (p == 1)
            {
                if (Ampel.phaseNr == 2 || Ampel.phaseNr == 3) //nicht während aktiverg grünphase Fußgänger dazu schalten, sondern erst beim nächsten mal
                {
                    Ampel.waitWalkerA = true;
                }
                else
                {
                    Ampel.walkerA = true;
                }
            }
            if (p == 2)
            {
                if (Ampel.phaseNr == 9 || Ampel.phaseNr == 10)
                {
                    Ampel.waitWalkerB = true;
                }
                else
                {
                    Ampel.walkerB = true;
                }
            }
        }
    }
}
