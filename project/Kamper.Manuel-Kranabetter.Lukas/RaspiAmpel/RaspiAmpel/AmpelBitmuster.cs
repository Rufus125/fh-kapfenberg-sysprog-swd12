using LibPiGpio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RaspiAmpel
{
    /// <summary>
    /// Schalten der Ampel mit einem "Bitmuster" - eine etwas andere Lösung ;)
    /// by Manuel Kamper
    /// </summary>
    class AmpelBitmuster
    {
        //Ampel Bitmuster - das Herzstück
        //1ro 1ge 1gr 2ro 2ge 2gr 3ro 3gr 4ro 4gr
        static string[] bitmuster = new string[]{
        "1001001010", //0
        "1101001010", //1
        "0011000110", //2
        "0011000210", //3
        "0011001010", //4
        "0021001010", //5
        "0101001010", //6
        "1001001010", //7
        "1001101010", //8
        "1000011001", //9
        "1000011002", //10
        "1000011010", //11
        "1000021010", //12
        "1000101010", //13
        };

        /// <summary>
        /// Generiert das benötigte Char-Array zum Schalten der Ampeln
        /// </summary>
        /// <param name="p">Phasennummer für Bitmuster</param>
        internal static void AmpelBit(int p)
        {
            char[] phaseBits = bitmuster[p].ToCharArray();

            //FußgängerRequests nach jeder Fußgängerphase zurücksetzen
            if(p==4)
            {
                Ampel.walkerA = false;
            }
            if (p == 11)
            {
                Ampel.walkerB = false;
            }

            WriteBitsToGpio(phaseBits);
        }

        /// <summary>
        /// Schaltet die Ampeln nach dem Bitmuster
        /// </summary>
        /// <param name="phaseBits"></param>
        internal static void WriteBitsToGpio(char[] phaseBits)
        {
            for (int i = 0; i < phaseBits.Length; i++)
            {
                //Fußgänger überschreiben wenn Ampel ein ist aber kein Request da ist
                if ((i == 6 || i == 7) && !Ampel.walkerA && Ampel.ampelAktiv)
                {
                    phaseBits[6] = '1';
                    phaseBits[7] = '0';
                }
                if ((i == 8 || i == 9) && !Ampel.walkerB && Ampel.ampelAktiv)
                {
                    phaseBits[8] = '1';
                    phaseBits[9] = '0';
                }

                //wartende Requests der Fußgänger aktiv stellen
                if(Ampel.phaseNr==5 || Ampel.phaseNr==12)
                {
                    if (Ampel.waitWalkerA) { Ampel.walkerA = true; Ampel.waitWalkerA = false; }
                    if (Ampel.waitWalkerB) { Ampel.walkerB = true; Ampel.waitWalkerB = false; }
                }

                char value = phaseBits[i];
                switch (phaseBits[i].ToString())
                {
                    case "1":
                        RpiGpio.Pins[Ampel.gpioOut[i]] = true;
                        break;
                    case "2":
                        RpiGpio.Pins[Ampel.gpioOut[i]] = !RpiGpio.Pins[Ampel.gpioOut[i]];
                        break;
                    default:
                        RpiGpio.Pins[Ampel.gpioOut[i]] = false;
                        break;
                }
            }
        }
    }
}
