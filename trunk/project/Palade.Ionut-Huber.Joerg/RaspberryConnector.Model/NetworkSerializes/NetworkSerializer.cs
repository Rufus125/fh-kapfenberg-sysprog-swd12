using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Xml;
using System.Xml.Serialization;

namespace RaspberryConnector.Model.NetworkSerializes
{
    public class NetworkSerializer
    {
        public string Serialize(object anySerializableObject)
        {
            var dto = SerializeToDTO(anySerializableObject);
            return XmlSerialize(dto);
        }

        public object Deserialize(string xmlDto)
        {
            var dto = XmlDeserialize(xmlDto);
            return DeserializeFromDTO(dto);
        }

        private static string XmlSerialize(NetworkDTO value)
        {
            var xmlserializer = new XmlSerializer(typeof(NetworkDTO));
            var stringWriter = new StringWriter();
            var writer = XmlWriter.Create(stringWriter);

            xmlserializer.Serialize(writer, value);

            var serializeXml = stringWriter.ToString();

            writer.Close();
            return serializeXml;
        }


        private static NetworkDTO XmlDeserialize(string input)
        {
            var ser = new XmlSerializer(typeof(NetworkDTO));

            using (var sr = new StringReader(input))
                return (NetworkDTO)ser.Deserialize(sr);
        }

        private static NetworkDTO SerializeToDTO(object anySerializableObject)
        {
            using (var memoryStream = new MemoryStream())
            {
                (new BinaryFormatter()).Serialize(memoryStream, anySerializableObject);
                return new NetworkDTO { Data = memoryStream.ToArray() };
            }
        }

        private static object DeserializeFromDTO(NetworkDTO message)
        {
            using (var memoryStream = new MemoryStream(message.Data))
                return (new BinaryFormatter()).Deserialize(memoryStream);
        }
    }


}
