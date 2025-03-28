#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <iostream>

void DATA_CALIBRATION() {
    
    const char* fileName = "cleaned_data.root"; // Hardcoded file name
    const char* treeName = "cleanedEventTRB"; // Hardcoded tree name

    TFile* file = TFile::Open(fileName, "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file " << fileName << std::endl;
        return;
    }

    // Get the tree
    TTree* tree = (TTree*)file->Get(treeName);
    if (!tree) {
        std::cerr << "Error: Tree " << treeName << " not found in file " << fileName << std::endl;
        file->Close();
        delete file;
        return;
    }

    const int nChannels = 383; // Number of channels
    std::vector<int> adcValues(nChannels);

    for (int ch = 0; ch < nChannels; ++ch) {
        tree->SetBranchAddress(Form("t_Ch%d", ch), &adcValues[ch]);
    }

    int eventNumber;
    std::cout << "Enter event number: ";
    std::cin >> eventNumber;

    if(eventNumber < 0 || eventNumber >= tree->GetEntries()) {
        std::cerr << "Error: Event number out of range." << std::endl;
        file->Close();
        delete file;
        return;
    }

    int nEntries = tree->GetEntries();

    std::vector<double> sigma(nChannels);

    for (int i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);

        for (int ch = 0; ch < nChannels; ++ch) {
            sigma[ch] += adcValues[ch];
        }
    }

    for (auto& value : sigma) {
        value = std::sqrt(value / nEntries);
    }


    std::map<int, int> validSums;
    int count = 0;
    for (int i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);

        int max = 0;
        int maxIdx = -1;
        for (int j = 0; j < adcValues.size(); ++j) {
            auto value = adcValues[j] / sigma[j];
            if (value < 18) {
                continue;
            }
            if (max < value) {
                max = value;
                maxIdx = j;
            }
        }
        if (maxIdx >= 0) {
            // std::cout << "max: " << max << " @ " << i << '\n';
            int sum = adcValues[maxIdx] / sigma[maxIdx];

            if (maxIdx > 0) {
                sum += adcValues[maxIdx - 1] / sigma[maxIdx - 1];
            }

            if (maxIdx < adcValues.size() - 1) {
                sum += adcValues[maxIdx + 1] / sigma[maxIdx + 1];
            }

            ++validSums[sum];

            ++count;

            // std::cout << "index " << i << '\n'; 

            // eventNumber = i;

            // break;
        }
    }
    std::cout << "count: " << count << " perc: " << ((count * 100) / nEntries) << '\n'
        << "valid disctinct sums: " << validSums.size() << '\n';

    TH1F* h1 = new TH1F("hEvent", Form("Event %d ADC Values;Channel;ADC Value", eventNumber), validSums.size(), 0, validSums.size());

    for (auto [sum, count] : validSums) {
        h1->SetBinContent(sum, count);
    }  

    h1->SetMinimum(0); // Set the minimum y value
    h1->SetMaximum(10000); // Set the maximum y value

    // Plotting
    TCanvas* c = new TCanvas("cEvent", Form("Event %d ADC Values", eventNumber), 1024, 768);
    h1->Draw();

    c->SaveAs(Form("cleanEvent%d.png", eventNumber));

 
    c->Connect("TCanvas", "Closed()", "TApplication", gApplication, "Terminate()");
    
    // Clean up
    delete h1;
    delete c;
    file->Close();
    delete file;
}

int main(int argc, char** argv) {
    TApplication app("app", &argc, argv);
    DATA_CALIBRATION();
    app.Run();
    return 0;
}
